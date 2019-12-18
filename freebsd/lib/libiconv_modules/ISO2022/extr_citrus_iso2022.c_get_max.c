#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int maxcharset; } ;
typedef  TYPE_1__ _ISO2022EncodingInfo ;

/* Variables and functions */
 int _MATCH ; 
 int _NOTMATCH ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static __inline int
get_max(_ISO2022EncodingInfo * __restrict ei,
    const char * __restrict token)
{
	if (!strcmp(token, "MAX1"))
		ei->maxcharset = 1;
	else if (!strcmp(token, "MAX2"))
		ei->maxcharset = 2;
	else if (!strcmp(token, "MAX3"))
		ei->maxcharset = 3;
	else
		return (_NOTMATCH);

	return (_MATCH);
}