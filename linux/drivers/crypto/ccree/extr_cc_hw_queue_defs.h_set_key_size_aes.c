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
typedef  int u32 ;
struct cc_hw_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_key_size (struct cc_hw_desc*,int) ; 

__attribute__((used)) static inline void set_key_size_aes(struct cc_hw_desc *pdesc, u32 size)
{
	set_key_size(pdesc, ((size >> 3) - 2));
}