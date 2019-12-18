#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct TYPE_2__* next; struct TYPE_2__* prev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/ * NB_Alloc ; 
 TYPE_1__ NB_Head ; 
 int /*<<< orphan*/  NB_MAGIC_ALLOCA ; 
 int /*<<< orphan*/  NB_max ; 
 int /*<<< orphan*/  NET_BUFFERS ; 
 long NET_BUFFER_ALIGN ; 
 int /*<<< orphan*/ * NetBufferSpace ; 

void init_netbuffers (void) {
  NB_max = NET_BUFFERS;
  NB_Head.state = NB_MAGIC_ALLOCA;
  NB_Head.prev = NB_Head.next = &NB_Head;
  NB_Alloc = &NetBufferSpace[(NET_BUFFER_ALIGN - (long) NetBufferSpace) & (NET_BUFFER_ALIGN - 1)];
}