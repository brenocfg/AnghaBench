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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  in_addr_t ;
typedef  int /*<<< orphan*/  dst ;

/* Variables and functions */
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int /*<<< orphan*/  fnv_32_buf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
in_gif_hashval(in_addr_t src, in_addr_t dst)
{
	uint32_t ret;

	ret = fnv_32_buf(&src, sizeof(src), FNV1_32_INIT);
	return (fnv_32_buf(&dst, sizeof(dst), ret));
}