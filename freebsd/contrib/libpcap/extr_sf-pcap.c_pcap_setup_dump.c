#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  tzoff; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  pcap_dumper_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  SET_BINMODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sf_write_header (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static pcap_dumper_t *
pcap_setup_dump(pcap_t *p, int linktype, FILE *f, const char *fname)
{

#if defined(_WIN32) || defined(MSDOS)
	/*
	 * If we're writing to the standard output, put it in binary
	 * mode, as savefiles are binary files.
	 *
	 * Otherwise, we turn off buffering.
	 * XXX - why?  And why not on the standard output?
	 */
	if (f == stdout)
		SET_BINMODE(f);
	else
		setvbuf(f, NULL, _IONBF, 0);
#endif
	if (sf_write_header(p, f, linktype, p->tzoff, p->snapshot) == -1) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "Can't write to %s", fname);
		if (f != stdout)
			(void)fclose(f);
		return (NULL);
	}
	return ((pcap_dumper_t *)f);
}