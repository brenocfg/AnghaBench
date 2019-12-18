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
struct asymmetric_key_ids {int /*<<< orphan*/ * id; } ;
struct asymmetric_key_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ asymmetric_key_id_same (int /*<<< orphan*/ ,struct asymmetric_key_id const*) ; 

__attribute__((used)) static bool match_either_id(const struct asymmetric_key_ids *pair,
			    const struct asymmetric_key_id *single)
{
	return (asymmetric_key_id_same(pair->id[0], single) ||
		asymmetric_key_id_same(pair->id[1], single));
}