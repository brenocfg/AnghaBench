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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int num_algo; int /*<<< orphan*/ * hmac; } ;
typedef  TYPE_1__ sctp_hmaclist_t ;
typedef  int /*<<< orphan*/  hmac_id ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
sctp_serialize_hmaclist(sctp_hmaclist_t *list, uint8_t *ptr)
{
	int i;
	uint16_t hmac_id;

	if (list == NULL)
		return (0);

	for (i = 0; i < list->num_algo; i++) {
		hmac_id = htons(list->hmac[i]);
		memcpy(ptr, &hmac_id, sizeof(hmac_id));
		ptr += sizeof(hmac_id);
	}
	return (list->num_algo * sizeof(hmac_id));
}