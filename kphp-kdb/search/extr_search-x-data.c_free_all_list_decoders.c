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
 int Q_decoders ; 
 int /*<<< orphan*/ * allocated_list_decoders ; 
 int /*<<< orphan*/  zfree_list_decoder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_all_list_decoders (void) {
  int i;
  for (i = 0; i < Q_decoders; i++) { zfree_list_decoder (allocated_list_decoders[i]); }
  Q_decoders = 0;
}