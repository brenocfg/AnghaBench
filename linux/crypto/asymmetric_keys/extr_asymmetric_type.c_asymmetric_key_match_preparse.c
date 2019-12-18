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
struct key_match_data {char* raw_data; int (* cmp ) (struct key const*,struct key_match_data const*) ;int /*<<< orphan*/  lookup_type; struct asymmetric_key_id* preparsed; } ;
struct asymmetric_key_id {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct asymmetric_key_id*) ; 
 int /*<<< orphan*/  KEYRING_SEARCH_LOOKUP_ITERATE ; 
 int PTR_ERR (struct asymmetric_key_id*) ; 
 int asymmetric_key_cmp (struct key const*,struct key_match_data const*) ; 
 int asymmetric_key_cmp_partial (struct key const*,struct key_match_data const*) ; 
 struct asymmetric_key_id* asymmetric_key_hex_to_key_id (char const*) ; 

__attribute__((used)) static int asymmetric_key_match_preparse(struct key_match_data *match_data)
{
	struct asymmetric_key_id *match_id;
	const char *spec = match_data->raw_data;
	const char *id;
	bool (*cmp)(const struct key *, const struct key_match_data *) =
		asymmetric_key_cmp;

	if (!spec || !*spec)
		return -EINVAL;
	if (spec[0] == 'i' &&
	    spec[1] == 'd' &&
	    spec[2] == ':') {
		id = spec + 3;
		cmp = asymmetric_key_cmp_partial;
	} else if (spec[0] == 'e' &&
		   spec[1] == 'x' &&
		   spec[2] == ':') {
		id = spec + 3;
	} else {
		goto default_match;
	}

	match_id = asymmetric_key_hex_to_key_id(id);
	if (IS_ERR(match_id))
		return PTR_ERR(match_id);

	match_data->preparsed = match_id;
	match_data->cmp = cmp;
	match_data->lookup_type = KEYRING_SEARCH_LOOKUP_ITERATE;
	return 0;

default_match:
	return 0;
}