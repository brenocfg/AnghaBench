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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* provider_p ;
typedef  int int32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int32_t
provider_update(provider_p provider, uint8_t const *data, uint32_t datalen)
{
	uint8_t	*new_data = (uint8_t *) realloc(provider->data, datalen);

	if (new_data == NULL)
		return (-1);

	memcpy(new_data, data, datalen);
	provider->data = new_data;

	return (0);
}