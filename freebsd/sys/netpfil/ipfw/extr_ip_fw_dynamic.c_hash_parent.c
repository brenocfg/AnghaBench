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
struct ipfw_flow_id {int dummy; } ;
typedef  int /*<<< orphan*/  rule ;

/* Variables and functions */
 int /*<<< orphan*/  hash_packet (struct ipfw_flow_id const*) ; 
 int /*<<< orphan*/  jenkins_hash32 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint32_t
hash_parent(const struct ipfw_flow_id *id, const void *rule)
{

	return (jenkins_hash32((const uint32_t *)&rule,
	    sizeof(rule) / sizeof(uint32_t), hash_packet(id)));
}