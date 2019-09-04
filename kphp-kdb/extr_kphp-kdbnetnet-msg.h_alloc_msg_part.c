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
struct msg_part {int dummy; } ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

__attribute__((used)) static inline struct msg_part *alloc_msg_part (void) { return (struct msg_part *) malloc (sizeof (struct msg_part)); }