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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/  ERR_EXISTS ; 
 int NOCLOBBER_ASK ; 
 int NOCLOBBER_NOTEMPTY ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ getYN (int /*<<< orphan*/ ) ; 
 int no_clobber ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
chkclob(const char *cp)
{
    struct stat stb;

    if (stat(cp, &stb) < 0)
	return;
    if (S_ISCHR(stb.st_mode))
	return;
    if (no_clobber & NOCLOBBER_NOTEMPTY && stb.st_size == 0)
	return;
    if (no_clobber & NOCLOBBER_ASK) {
	if (getYN(CGETS(22, 15,
	    "Do you really want to overwrite an existing file? [N/y] ")))
	    return;
    }

    stderror(ERR_EXISTS, cp);
}