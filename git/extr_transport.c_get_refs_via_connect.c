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
struct transport {int dummy; } ;
struct ref {int dummy; } ;
struct argv_array {int dummy; } ;

/* Variables and functions */
 struct ref* handshake (struct transport*,int,struct argv_array const*,int) ; 

__attribute__((used)) static struct ref *get_refs_via_connect(struct transport *transport, int for_push,
					const struct argv_array *ref_prefixes)
{
	return handshake(transport, for_push, ref_prefixes, 1);
}