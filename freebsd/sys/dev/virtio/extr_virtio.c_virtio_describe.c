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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
struct virtio_feature_desc {int dummy; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int VIRTIO_F_BAD_FEATURE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char const*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 scalar_t__ sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sbuf_overflowed (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*,...) ; 
 char* virtio_feature_name (int,struct virtio_feature_desc*) ; 

void
virtio_describe(device_t dev, const char *msg,
    uint64_t features, struct virtio_feature_desc *desc)
{
	struct sbuf sb;
	uint64_t val;
	char *buf;
	const char *name;
	int n;

	if ((buf = malloc(512, M_TEMP, M_NOWAIT)) == NULL) {
		device_printf(dev, "%s features: %#jx\n", msg, (uintmax_t) features);
		return;
	}

	sbuf_new(&sb, buf, 512, SBUF_FIXEDLEN);
	sbuf_printf(&sb, "%s features: %#jx", msg, (uintmax_t) features);

	for (n = 0, val = 1ULL << 63; val != 0; val >>= 1) {
		/*
		 * BAD_FEATURE is used to detect broken Linux clients
		 * and therefore is not applicable to FreeBSD.
		 */
		if (((features & val) == 0) || val == VIRTIO_F_BAD_FEATURE)
			continue;

		if (n++ == 0)
			sbuf_cat(&sb, " <");
		else
			sbuf_cat(&sb, ",");

		name = virtio_feature_name(val, desc);
		if (name == NULL)
			sbuf_printf(&sb, "%#jx", (uintmax_t) val);
		else
			sbuf_cat(&sb, name);
	}

	if (n > 0)
		sbuf_cat(&sb, ">");

#if __FreeBSD_version < 900020
	sbuf_finish(&sb);
	if (sbuf_overflowed(&sb) == 0)
#else
	if (sbuf_finish(&sb) == 0)
#endif
		device_printf(dev, "%s\n", sbuf_data(&sb));

	sbuf_delete(&sb);
	free(buf, M_TEMP);
}