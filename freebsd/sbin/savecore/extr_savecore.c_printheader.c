#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xo_handle_t ;
typedef  void* uint64_t ;
typedef  void* time_t ;
struct kerneldumpheader {char const* architecture; int compression; char const* hostname; char const* magic; char const* versionstring; char const* panicstring; char const* parity; int /*<<< orphan*/  dumptime; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  dumplength; int /*<<< orphan*/  architectureversion; } ;

/* Variables and functions */
#define  KERNELDUMP_COMP_GZIP 132 
#define  KERNELDUMP_COMP_NONE 131 
#define  KERNELDUMP_COMP_ZSTD 130 
#define  STATUS_BAD 129 
#define  STATUS_GOOD 128 
 char const* ctime (void**) ; 
 char const* dtoh32 (int /*<<< orphan*/ ) ; 
 void* dtoh64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_emit_h (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  xo_flush_h (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
printheader(xo_handle_t *xo, const struct kerneldumpheader *h,
    const char *device, int bounds, const int status)
{
	uint64_t dumplen;
	time_t t;
	const char *stat_str;
	const char *comp_str;

	xo_flush_h(xo);
	xo_emit_h(xo, "{Lwc:Dump header from device}{:dump_device/%s}\n",
	    device);
	xo_emit_h(xo, "{P:  }{Lwc:Architecture}{:architecture/%s}\n",
	    h->architecture);
	xo_emit_h(xo,
	    "{P:  }{Lwc:Architecture Version}{:architecture_version/%u}\n",
	    dtoh32(h->architectureversion));
	dumplen = dtoh64(h->dumplength);
	xo_emit_h(xo, "{P:  }{Lwc:Dump Length}{:dump_length_bytes/%lld}\n",
	    (long long)dumplen);
	xo_emit_h(xo, "{P:  }{Lwc:Blocksize}{:blocksize/%d}\n",
	    dtoh32(h->blocksize));
	switch (h->compression) {
	case KERNELDUMP_COMP_NONE:
		comp_str = "none";
		break;
	case KERNELDUMP_COMP_GZIP:
		comp_str = "gzip";
		break;
	case KERNELDUMP_COMP_ZSTD:
		comp_str = "zstd";
		break;
	default:
		comp_str = "???";
		break;
	}
	xo_emit_h(xo, "{P:  }{Lwc:Compression}{:compression/%s}\n", comp_str);
	t = dtoh64(h->dumptime);
	xo_emit_h(xo, "{P:  }{Lwc:Dumptime}{:dumptime/%s}", ctime(&t));
	xo_emit_h(xo, "{P:  }{Lwc:Hostname}{:hostname/%s}\n", h->hostname);
	xo_emit_h(xo, "{P:  }{Lwc:Magic}{:magic/%s}\n", h->magic);
	xo_emit_h(xo, "{P:  }{Lwc:Version String}{:version_string/%s}",
	    h->versionstring);
	xo_emit_h(xo, "{P:  }{Lwc:Panic String}{:panic_string/%s}\n",
	    h->panicstring);
	xo_emit_h(xo, "{P:  }{Lwc:Dump Parity}{:dump_parity/%u}\n", h->parity);
	xo_emit_h(xo, "{P:  }{Lwc:Bounds}{:bounds/%d}\n", bounds);

	switch (status) {
	case STATUS_BAD:
		stat_str = "bad";
		break;
	case STATUS_GOOD:
		stat_str = "good";
		break;
	default:
		stat_str = "unknown";
		break;
	}
	xo_emit_h(xo, "{P:  }{Lwc:Dump Status}{:dump_status/%s}\n", stat_str);
	xo_flush_h(xo);
}