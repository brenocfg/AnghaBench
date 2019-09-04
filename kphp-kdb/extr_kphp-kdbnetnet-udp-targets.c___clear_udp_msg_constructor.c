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
struct udp_msg_constructor {int total_parts; TYPE_1__* msgs; } ;
struct TYPE_2__ {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct udp_msg_constructor*) ; 
 int /*<<< orphan*/  rwm_free (TYPE_1__*) ; 

void __clear_udp_msg_constructor (struct udp_msg_constructor *M) {
  int i;
  for (i = 0; i < M->total_parts; i++) {
    if (M->msgs[i].magic) {
      rwm_free (&M->msgs[i]);
    }
  }
  free (M);
}