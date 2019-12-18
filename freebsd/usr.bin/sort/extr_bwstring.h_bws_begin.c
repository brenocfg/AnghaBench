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
struct bwstring {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  bwstring_iterator ;

/* Variables and functions */

__attribute__((used)) static inline bwstring_iterator
bws_begin(struct bwstring *bws)
{

	return (bwstring_iterator) (&(bws->data));
}