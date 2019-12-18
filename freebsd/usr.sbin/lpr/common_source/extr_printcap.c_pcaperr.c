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
#define  PCAPERR_NOTFOUND 132 
#define  PCAPERR_OSERR 131 
#define  PCAPERR_SUCCESS 130 
#define  PCAPERR_TCLOOP 129 
#define  PCAPERR_TCOPEN 128 
 int /*<<< orphan*/  errno ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

const char *
pcaperr(int error)
{
	switch(error) {
	case PCAPERR_TCOPEN:
		return "unresolved tc= expansion";
	case PCAPERR_SUCCESS:
		return "no error";
	case PCAPERR_NOTFOUND:
		return "printer not found";
	case PCAPERR_OSERR:
		return strerror(errno);
	case PCAPERR_TCLOOP:
		return "loop detected in tc= expansion";
	default:
		return "unknown printcap error";
	}
}