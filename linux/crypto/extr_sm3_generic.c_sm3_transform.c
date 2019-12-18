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
typedef  int /*<<< orphan*/  wt ;
typedef  int /*<<< orphan*/  w ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sm3_state {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  memzero_explicit (unsigned int*,int) ; 
 int /*<<< orphan*/  sm3_compress (unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm3_expand (int /*<<< orphan*/ *,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void sm3_transform(struct sm3_state *sst, u8 const *src)
{
	unsigned int w[68];
	unsigned int wt[64];

	sm3_expand((u32 *)src, w, wt);
	sm3_compress(w, wt, sst->state);

	memzero_explicit(w, sizeof(w));
	memzero_explicit(wt, sizeof(wt));
}