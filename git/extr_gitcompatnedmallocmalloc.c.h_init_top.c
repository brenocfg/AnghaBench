#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  TYPE_2__* mchunkptr ;
struct TYPE_12__ {int /*<<< orphan*/  head; } ;
struct TYPE_11__ {int /*<<< orphan*/  trim_threshold; } ;
struct TYPE_10__ {size_t head; } ;
struct TYPE_9__ {size_t topsize; int /*<<< orphan*/  trim_check; TYPE_2__* top; } ;

/* Variables and functions */
 size_t PINUSE_BIT ; 
 int /*<<< orphan*/  TOP_FOOT_SIZE ; 
 size_t align_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk2mem (TYPE_2__*) ; 
 TYPE_6__* chunk_plus_offset (TYPE_2__*,size_t) ; 
 TYPE_3__ mparams ; 

__attribute__((used)) static void init_top(mstate m, mchunkptr p, size_t psize) {
  /* Ensure alignment */
  size_t offset = align_offset(chunk2mem(p));
  p = (mchunkptr)((char*)p + offset);
  psize -= offset;

  m->top = p;
  m->topsize = psize;
  p->head = psize | PINUSE_BIT;
  /* set size of fake trailing chunk holding overhead space only once */
  chunk_plus_offset(p, psize)->head = TOP_FOOT_SIZE;
  m->trim_check = mparams.trim_threshold; /* reset on each update */
}