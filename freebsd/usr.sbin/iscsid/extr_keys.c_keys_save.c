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
struct pdu {char* pdu_data; size_t pdu_data_len; } ;
struct keys {char** keys_names; char** keys_values; } ;

/* Variables and functions */
 int KEYS_MAX ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void
keys_save(struct keys *keys, struct pdu *pdu)
{
	char *data;
	size_t len;
	int i;

	/*
	 * XXX: Not particularly efficient.
	 */
	len = 0;
	for (i = 0; i < KEYS_MAX; i++) {
		if (keys->keys_names[i] == NULL)
			break;
		/*
		 * +1 for '=', +1 for '\0'.
		 */
		len += strlen(keys->keys_names[i]) +
		    strlen(keys->keys_values[i]) + 2;
	}

	if (len == 0)
		return;

	data = malloc(len);
	if (data == NULL)
		log_err(1, "malloc");

	pdu->pdu_data = data;
	pdu->pdu_data_len = len;

	for (i = 0; i < KEYS_MAX; i++) {
		if (keys->keys_names[i] == NULL)
			break;
		data += sprintf(data, "%s=%s",
		    keys->keys_names[i], keys->keys_values[i]);
		data += 1; /* for '\0'. */
	}
}