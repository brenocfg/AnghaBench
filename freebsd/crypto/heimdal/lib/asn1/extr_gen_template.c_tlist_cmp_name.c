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
struct tlist {int dummy; } ;

/* Variables and functions */
 int tlist_cmp (struct tlist*,struct tlist*) ; 
 struct tlist* tlist_find_by_name (char const*) ; 

__attribute__((used)) static int
tlist_cmp_name(const char *tname, const char *qname)
{
    struct tlist *tl = tlist_find_by_name(tname);
    struct tlist *ql = tlist_find_by_name(qname);
    return tlist_cmp(tl, ql);
}