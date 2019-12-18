#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int warc_type_t ;
struct TYPE_8__ {unsigned int len; char* str; } ;
typedef  TYPE_3__ warc_string_t ;
typedef  scalar_t__ time_t ;
struct TYPE_7__ {unsigned int len; char* str; } ;
struct warc_s {unsigned int pver; unsigned int cntoff; TYPE_2__ pool; scalar_t__ cntlen; int /*<<< orphan*/  sver; } ;
struct TYPE_9__ {int /*<<< orphan*/  archive_format; } ;
struct archive_read {TYPE_4__ archive; TYPE_1__* format; } ;
struct archive_entry {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {struct warc_s* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_WARC ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  HDR_PROBE_LEN ; 
#define  WT_RSP 129 
#define  WT_RSRC 128 
 char* __archive_read_ahead (struct archive_read*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,int) ; 
 char* _warc_find_eoh (char const*,scalar_t__) ; 
 scalar_t__ _warc_rdlen (char const*,int) ; 
 scalar_t__ _warc_rdmtm (char const*,int) ; 
 scalar_t__ _warc_rdrtm (char const*,int) ; 
 int _warc_rdtyp (char const*,int) ; 
 TYPE_3__ _warc_rduri (char const*,int) ; 
 unsigned int _warc_rdver (char const*,int) ; 
 int /*<<< orphan*/  _warc_skip (struct archive_read*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_set_ctime (struct archive_entry*,scalar_t__,long) ; 
 int /*<<< orphan*/  archive_entry_set_filetype (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,scalar_t__,long) ; 
 int /*<<< orphan*/  archive_entry_set_perm (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  archive_string_sprintf (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 char* realloc (char*,unsigned int) ; 

__attribute__((used)) static int
_warc_rdhdr(struct archive_read *a, struct archive_entry *entry)
{
#define HDR_PROBE_LEN		(12U)
	struct warc_s *w = a->format->data;
	unsigned int ver;
	const char *buf;
	ssize_t nrd;
	const char *eoh;
	/* for the file name, saves some strndup()'ing */
	warc_string_t fnam;
	/* warc record type, not that we really use it a lot */
	warc_type_t ftyp;
	/* content-length+error monad */
	ssize_t cntlen;
	/* record time is the WARC-Date time we reinterpret it as ctime */
	time_t rtime;
	/* mtime is the Last-Modified time which will be the entry's mtime */
	time_t mtime;

start_over:
	/* just use read_ahead() they keep track of unconsumed
	 * bits and bobs for us; no need to put an extra shift in
	 * and reproduce that functionality here */
	buf = __archive_read_ahead(a, HDR_PROBE_LEN, &nrd);

	if (nrd < 0) {
		/* no good */
		archive_set_error(
			&a->archive, ARCHIVE_ERRNO_MISC,
			"Bad record header");
		return (ARCHIVE_FATAL);
	} else if (buf == NULL) {
		/* there should be room for at least WARC/bla\r\n
		 * must be EOF therefore */
		return (ARCHIVE_EOF);
	}
 	/* looks good so far, try and find the end of the header now */
	eoh = _warc_find_eoh(buf, nrd);
	if (eoh == NULL) {
		/* still no good, the header end might be beyond the
		 * probe we've requested, but then again who'd cram
		 * so much stuff into the header *and* be 28500-compliant */
		archive_set_error(
			&a->archive, ARCHIVE_ERRNO_MISC,
			"Bad record header");
		return (ARCHIVE_FATAL);
	}
	ver = _warc_rdver(buf, eoh - buf);
	/* we currently support WARC 0.12 to 1.0 */
	if (ver == 0U) {
		archive_set_error(
			&a->archive, ARCHIVE_ERRNO_MISC,
			"Invalid record version");
		return (ARCHIVE_FATAL);
	} else if (ver < 1200U || ver > 10000U) {
		archive_set_error(
			&a->archive, ARCHIVE_ERRNO_MISC,
			"Unsupported record version: %u.%u",
			ver / 10000, (ver % 10000) / 100);
		return (ARCHIVE_FATAL);
	}
	cntlen = _warc_rdlen(buf, eoh - buf);
	if (cntlen < 0) {
		/* nightmare!  the specs say content-length is mandatory
		 * so I don't feel overly bad stopping the reader here */
		archive_set_error(
			&a->archive, EINVAL,
			"Bad content length");
		return (ARCHIVE_FATAL);
	}
	rtime = _warc_rdrtm(buf, eoh - buf);
	if (rtime == (time_t)-1) {
		/* record time is mandatory as per WARC/1.0,
		 * so just barf here, fast and loud */
		archive_set_error(
			&a->archive, EINVAL,
			"Bad record time");
		return (ARCHIVE_FATAL);
	}

	/* let the world know we're a WARC archive */
	a->archive.archive_format = ARCHIVE_FORMAT_WARC;
	if (ver != w->pver) {
		/* stringify this entry's version */
		archive_string_sprintf(&w->sver,
			"WARC/%u.%u", ver / 10000, (ver % 10000) / 100);
		/* remember the version */
		w->pver = ver;
	}
	/* start off with the type */
	ftyp = _warc_rdtyp(buf, eoh - buf);
	/* and let future calls know about the content */
	w->cntlen = cntlen;
	w->cntoff = 0U;
	mtime = 0;/* Avoid compiling error on some platform. */

	switch (ftyp) {
	case WT_RSRC:
	case WT_RSP:
		/* only try and read the filename in the cases that are
		 * guaranteed to have one */
		fnam = _warc_rduri(buf, eoh - buf);
		/* check the last character in the URI to avoid creating
		 * directory endpoints as files, see Todo above */
		if (fnam.len == 0 || fnam.str[fnam.len - 1] == '/') {
			/* break here for now */
			fnam.len = 0U;
			fnam.str = NULL;
			break;
		}
		/* bang to our string pool, so we save a
		 * malloc()+free() roundtrip */
		if (fnam.len + 1U > w->pool.len) {
			w->pool.len = ((fnam.len + 64U) / 64U) * 64U;
			w->pool.str = realloc(w->pool.str, w->pool.len);
		}
		memcpy(w->pool.str, fnam.str, fnam.len);
		w->pool.str[fnam.len] = '\0';
		/* let no one else know about the pool, it's a secret, shhh */
		fnam.str = w->pool.str;

		/* snarf mtime or deduce from rtime
		 * this is a custom header added by our writer, it's quite
		 * hard to believe anyone else would go through with it
		 * (apart from being part of some http responses of course) */
		if ((mtime = _warc_rdmtm(buf, eoh - buf)) == (time_t)-1) {
			mtime = rtime;
		}
		break;
	default:
		fnam.len = 0U;
		fnam.str = NULL;
		break;
	}

	/* now eat some of those delicious buffer bits */
	__archive_read_consume(a, eoh - buf);

	switch (ftyp) {
	case WT_RSRC:
	case WT_RSP:
		if (fnam.len > 0U) {
			/* populate entry object */
			archive_entry_set_filetype(entry, AE_IFREG);
			archive_entry_copy_pathname(entry, fnam.str);
			archive_entry_set_size(entry, cntlen);
			archive_entry_set_perm(entry, 0644);
			/* rtime is the new ctime, mtime stays mtime */
			archive_entry_set_ctime(entry, rtime, 0L);
			archive_entry_set_mtime(entry, mtime, 0L);
			break;
		}
		/* FALLTHROUGH */
	default:
		/* consume the content and start over */
		_warc_skip(a);
		goto start_over;
	}
	return (ARCHIVE_OK);
}