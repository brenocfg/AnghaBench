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
struct key {int key_id; int key_len; int /*<<< orphan*/  key_seq; int /*<<< orphan*/  typen; } ;

/* Variables and functions */
 int CompareKeys (struct key,struct key) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

bool
CompareKeysAlternative(
	int		key_id,
	int		key_len,
	const char *	type,
	const char *	key_seq,
	struct key	actual
	)
{
	struct key	temp;

	temp.key_id = key_id;
	temp.key_len = key_len;
	strlcpy(temp.typen, type, sizeof(temp.typen));
	memcpy(temp.key_seq, key_seq, key_len);

	return CompareKeys(temp, actual);
}