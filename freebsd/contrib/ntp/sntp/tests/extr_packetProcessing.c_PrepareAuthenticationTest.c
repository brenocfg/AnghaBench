#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct key {int dummy; } ;
struct TYPE_3__ {int key_id; int key_len; int /*<<< orphan*/  key_seq; int /*<<< orphan*/  typen; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateOption (char*,char*) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int) ; 
 TYPE_1__* emalloc (int) ; 
 int key_cnt ; 
 TYPE_1__* key_ptr ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int restoreKeyDb ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strlen (char const*) ; 

void
PrepareAuthenticationTest(
	int		key_id,
	int		key_len,
	const char *	type,
	const void *	key_seq
	)
{
	char str[25];
	snprintf(str, 25, "%d", key_id);
	ActivateOption("-a", str);

	key_cnt = 1;
	key_ptr = emalloc(sizeof(struct key));
	key_ptr->next = NULL;
	key_ptr->key_id = key_id;
	key_ptr->key_len = key_len;
	memcpy(key_ptr->typen, type, strlen(type) + 1);

	TEST_ASSERT_TRUE(key_len < sizeof(key_ptr->key_seq));

	memcpy(key_ptr->key_seq, key_seq, key_ptr->key_len);
	restoreKeyDb = true;
}