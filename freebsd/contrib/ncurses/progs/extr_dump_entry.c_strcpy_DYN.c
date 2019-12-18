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
struct TYPE_4__ {scalar_t__ used; } ;
typedef  TYPE_1__ DYNBUF ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncpy_DYN (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
strcpy_DYN(DYNBUF * dst, const char *src)
{
    if (src == 0) {
	dst->used = 0;
	strcpy_DYN(dst, "");
    } else {
	strncpy_DYN(dst, src, strlen(src));
    }
}