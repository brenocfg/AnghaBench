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

/* Variables and functions */
#define  E2BIG 130 
#define  EILSEQ 129 
#define  EINVAL 128 
 int MB_TO_UC_FLAG ; 
 int MB_TO_WC_FLAG ; 
 int UC_TO_MB_FLAG ; 
 int WC_TO_MB_FLAG ; 
 int fb_flags ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static void
format_diag(int errcode)
{
	const char *errstr;
	const char *u2m, *m2u, *m2w, *w2m;

	switch (errcode) {
	case EINVAL:
		errstr = "EINVAL ";
		break;
	case EILSEQ:
		errstr = "EILSEQ ";
		break;
	case E2BIG:
		errstr = "E2BIG ";
		break;
	default:
		errstr = "UNKNOWN ";
		break;
	}
	
	u2m = (fb_flags & UC_TO_MB_FLAG) ? "U2M " : "";
	m2w = (fb_flags & MB_TO_WC_FLAG) ? "M2W " : "";
	m2u = (fb_flags & MB_TO_UC_FLAG) ? "M2U " : "";
	w2m = (fb_flags & WC_TO_MB_FLAG) ? "W2M " : "";

	printf("%s%s%s%s%s", errstr, u2m, m2w, m2u, w2m);
}