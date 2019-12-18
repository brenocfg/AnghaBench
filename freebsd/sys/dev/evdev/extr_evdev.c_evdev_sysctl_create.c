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
struct sysctl_oid {int dummy; } ;
struct evdev_dev {int ev_unit; int /*<<< orphan*/  ev_sw_flags; int /*<<< orphan*/  ev_sysctl_ctx; int /*<<< orphan*/  ev_snd_flags; int /*<<< orphan*/  ev_led_flags; int /*<<< orphan*/  ev_msc_flags; int /*<<< orphan*/  ev_abs_flags; int /*<<< orphan*/  ev_rel_flags; int /*<<< orphan*/  ev_key_flags; int /*<<< orphan*/  ev_type_flags; int /*<<< orphan*/  ev_prop_flags; int /*<<< orphan*/  ev_serial; int /*<<< orphan*/  ev_shortname; int /*<<< orphan*/  ev_id; int /*<<< orphan*/  ev_name; } ;
typedef  int /*<<< orphan*/  ev_unit_str ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE_WITH_LABEL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_OPAQUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRUCT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _kern_evdev_input ; 
 int /*<<< orphan*/  input_id ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
evdev_sysctl_create(struct evdev_dev *evdev)
{
	struct sysctl_oid *ev_sysctl_tree;
	char ev_unit_str[8];

	snprintf(ev_unit_str, sizeof(ev_unit_str), "%d", evdev->ev_unit);
	sysctl_ctx_init(&evdev->ev_sysctl_ctx);

	ev_sysctl_tree = SYSCTL_ADD_NODE_WITH_LABEL(&evdev->ev_sysctl_ctx,
	    SYSCTL_STATIC_CHILDREN(_kern_evdev_input), OID_AUTO,
	    ev_unit_str, CTLFLAG_RD, NULL, "", "device index");

	SYSCTL_ADD_STRING(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "name", CTLFLAG_RD,
	    evdev->ev_name, 0,
	    "Input device name");

	SYSCTL_ADD_STRUCT(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "id", CTLFLAG_RD,
	    &evdev->ev_id, input_id,
	    "Input device identification");

	/* ioctl returns ENOENT if phys is not set. sysctl returns "" here */
	SYSCTL_ADD_STRING(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "phys", CTLFLAG_RD,
	    evdev->ev_shortname, 0,
	    "Input device short name");

	/* ioctl returns ENOENT if uniq is not set. sysctl returns "" here */
	SYSCTL_ADD_STRING(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "uniq", CTLFLAG_RD,
	    evdev->ev_serial, 0,
	    "Input device unique number");

	SYSCTL_ADD_OPAQUE(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "props", CTLFLAG_RD,
	    evdev->ev_prop_flags, sizeof(evdev->ev_prop_flags), "",
	    "Input device properties");

	SYSCTL_ADD_OPAQUE(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "type_bits", CTLFLAG_RD,
	    evdev->ev_type_flags, sizeof(evdev->ev_type_flags), "",
	    "Input device supported events types");

	SYSCTL_ADD_OPAQUE(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "key_bits", CTLFLAG_RD,
	    evdev->ev_key_flags, sizeof(evdev->ev_key_flags),
	    "", "Input device supported keys");

	SYSCTL_ADD_OPAQUE(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "rel_bits", CTLFLAG_RD,
	    evdev->ev_rel_flags, sizeof(evdev->ev_rel_flags), "",
	    "Input device supported relative events");

	SYSCTL_ADD_OPAQUE(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "abs_bits", CTLFLAG_RD,
	    evdev->ev_abs_flags, sizeof(evdev->ev_abs_flags), "",
	    "Input device supported absolute events");

	SYSCTL_ADD_OPAQUE(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "msc_bits", CTLFLAG_RD,
	    evdev->ev_msc_flags, sizeof(evdev->ev_msc_flags), "",
	    "Input device supported miscellaneous events");

	SYSCTL_ADD_OPAQUE(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "led_bits", CTLFLAG_RD,
	    evdev->ev_led_flags, sizeof(evdev->ev_led_flags), "",
	    "Input device supported LED events");

	SYSCTL_ADD_OPAQUE(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "snd_bits", CTLFLAG_RD,
	    evdev->ev_snd_flags, sizeof(evdev->ev_snd_flags), "",
	    "Input device supported sound events");

	SYSCTL_ADD_OPAQUE(&evdev->ev_sysctl_ctx,
	    SYSCTL_CHILDREN(ev_sysctl_tree), OID_AUTO, "sw_bits", CTLFLAG_RD,
	    evdev->ev_sw_flags, sizeof(evdev->ev_sw_flags), "",
	    "Input device supported switch events");
}