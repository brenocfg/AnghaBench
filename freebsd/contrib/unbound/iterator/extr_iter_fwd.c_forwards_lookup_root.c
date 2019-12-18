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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iter_forwards {int dummy; } ;
struct delegpt {int dummy; } ;

/* Variables and functions */
 struct delegpt* forwards_lookup (struct iter_forwards*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct delegpt* 
forwards_lookup_root(struct iter_forwards* fwd, uint16_t qclass)
{
	uint8_t root = 0;
	return forwards_lookup(fwd, &root, qclass);
}