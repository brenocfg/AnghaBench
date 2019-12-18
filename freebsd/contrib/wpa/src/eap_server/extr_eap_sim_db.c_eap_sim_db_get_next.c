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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sim_db_data {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 char* os_malloc (int) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char * eap_sim_db_get_next(struct eap_sim_db_data *data, char prefix)
{
	char *id, *pos, *end;
	u8 buf[10];

	if (random_get_bytes(buf, sizeof(buf)))
		return NULL;
	id = os_malloc(sizeof(buf) * 2 + 2);
	if (id == NULL)
		return NULL;

	pos = id;
	end = id + sizeof(buf) * 2 + 2;
	*pos++ = prefix;
	wpa_snprintf_hex(pos, end - pos, buf, sizeof(buf));
	
	return id;
}