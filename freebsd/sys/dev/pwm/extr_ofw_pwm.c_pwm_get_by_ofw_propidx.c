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
struct pwm_channel {void* flags; void* period; void* channel; int /*<<< orphan*/ * dev; } ;
typedef  struct pwm_channel* pwm_channel_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  void* pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_prop_free (void**) ; 
 struct pwm_channel* malloc (int,int /*<<< orphan*/ ,int) ; 
 int ofw_bus_parse_xref_list_alloc (int /*<<< orphan*/ ,char const*,char*,int,int /*<<< orphan*/ *,int*,void***) ; 

int
pwm_get_by_ofw_propidx(device_t consumer, phandle_t node,
    const char *prop_name, int idx, pwm_channel_t *out_channel)
{
	phandle_t xref;
	pcell_t *cells;
	struct pwm_channel channel;
	int ncells, rv;

	rv = ofw_bus_parse_xref_list_alloc(node, prop_name, "#pwm-cells",
	  idx, &xref, &ncells, &cells);
	if (rv != 0)
		return (rv);

	channel.dev = OF_device_from_xref(xref);
	if (channel.dev == NULL) {
		OF_prop_free(cells);
		return (ENODEV);
	}

	channel.channel = cells[0];
	channel.period = cells[1];

	if (ncells >= 3)
		channel.flags = cells[2];

	*out_channel = malloc(sizeof(struct pwm_channel), M_DEVBUF, M_WAITOK | M_ZERO);
	**out_channel = channel;
	return (0);
}