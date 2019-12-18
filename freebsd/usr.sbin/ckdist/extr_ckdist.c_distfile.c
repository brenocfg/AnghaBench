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
 int DISTMD5 ; 
 int disttype (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int
distfile(const char *path)
{
    const char *s;
    int type;

    if ((type = disttype(path)) == DISTMD5 ||
	((s = strrchr(path, '.')) != NULL && s > path &&
	 (type = disttype(s + 1)) != 0))
	return type;
    return 0;
}