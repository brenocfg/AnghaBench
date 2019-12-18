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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  capp ;

/* Variables and functions */
 int EINVAL ; 
 int VIA_HAS_AES ; 
 int VIA_HAS_AESCTR ; 
 int VIA_HAS_MM ; 
 int VIA_HAS_SHA ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int via_feature_xcrypt ; 

__attribute__((used)) static int
padlock_probe(device_t dev)
{
	char capp[256];

#if defined(__amd64__) || defined(__i386__)
	/* If there is no AES support, we has nothing to do here. */
	if (!(via_feature_xcrypt & VIA_HAS_AES)) {
		device_printf(dev, "No ACE support.\n");
		return (EINVAL);
	}
	strlcpy(capp, "AES-CBC", sizeof(capp));
#if 0
	strlcat(capp, ",AES-EBC", sizeof(capp));
	strlcat(capp, ",AES-CFB", sizeof(capp));
	strlcat(capp, ",AES-OFB", sizeof(capp));
#endif
	if (via_feature_xcrypt & VIA_HAS_SHA) {
		strlcat(capp, ",SHA1", sizeof(capp));
		strlcat(capp, ",SHA256", sizeof(capp));
	}
#if 0
	if (via_feature_xcrypt & VIA_HAS_AESCTR)
		strlcat(capp, ",AES-CTR", sizeof(capp));
	if (via_feature_xcrypt & VIA_HAS_MM)
		strlcat(capp, ",RSA", sizeof(capp));
#endif
	device_set_desc_copy(dev, capp);
	return (0);
#else
	return (EINVAL);
#endif
}