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
struct mkuz_blk {size_t alen; int /*<<< orphan*/  br_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFSET_UNDEF ; 
 struct mkuz_blk* mkuz_safe_zmalloc (int) ; 

struct mkuz_blk *
mkuz_blk_ctor(size_t blen)
{
    struct mkuz_blk *rval;

    rval = mkuz_safe_zmalloc(sizeof(struct mkuz_blk) + blen);
    rval->alen = blen;
    rval->br_offset = OFFSET_UNDEF;
    return (rval);
}