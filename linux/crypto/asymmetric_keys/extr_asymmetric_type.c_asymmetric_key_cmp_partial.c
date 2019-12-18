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
struct key_match_data {struct asymmetric_key_id* preparsed; } ;
struct key {int dummy; } ;
struct asymmetric_key_ids {int dummy; } ;
struct asymmetric_key_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asymmetric_key_id_partial ; 
 struct asymmetric_key_ids* asymmetric_key_ids (struct key const*) ; 
 int asymmetric_match_key_ids (struct asymmetric_key_ids const*,struct asymmetric_key_id const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool asymmetric_key_cmp_partial(const struct key *key,
				       const struct key_match_data *match_data)
{
	const struct asymmetric_key_ids *kids = asymmetric_key_ids(key);
	const struct asymmetric_key_id *match_id = match_data->preparsed;

	return asymmetric_match_key_ids(kids, match_id,
					asymmetric_key_id_partial);
}