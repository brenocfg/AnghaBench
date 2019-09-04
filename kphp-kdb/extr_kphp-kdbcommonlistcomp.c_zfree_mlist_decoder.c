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
struct mlist_decoder {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfree (struct mlist_decoder*,int /*<<< orphan*/ ) ; 

void zfree_mlist_decoder (struct mlist_decoder *dec) {
  zfree (dec, dec->size);
}