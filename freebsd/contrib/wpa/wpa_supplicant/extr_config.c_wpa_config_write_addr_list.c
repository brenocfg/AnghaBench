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
struct parse_data {int dummy; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int hwaddr_mask_txt (char*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 

__attribute__((used)) static char * wpa_config_write_addr_list(const struct parse_data *data,
					 const u8 *list, size_t num, char *name)
{
	char *value, *end, *pos;
	int res;
	size_t i;

	if (list == NULL || num == 0)
		return NULL;

	value = os_malloc(2 * 20 * num);
	if (value == NULL)
		return NULL;
	pos = value;
	end = value + 2 * 20 * num;

	for (i = num; i > 0; i--) {
		const u8 *a = list + (i - 1) * 2 * ETH_ALEN;
		const u8 *m = a + ETH_ALEN;

		if (i < num)
			*pos++ = ' ';
		res = hwaddr_mask_txt(pos, end - pos, a, m);
		if (res < 0) {
			os_free(value);
			return NULL;
		}
		pos += res;
	}

	return value;
}