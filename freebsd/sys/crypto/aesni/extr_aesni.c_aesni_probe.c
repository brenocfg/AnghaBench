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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  detect_cpu_features (int*,int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
aesni_probe(device_t dev)
{
	bool has_aes, has_sha;

	detect_cpu_features(&has_aes, &has_sha);
	if (!has_aes && !has_sha) {
		device_printf(dev, "No AES or SHA support.\n");
		return (EINVAL);
	} else if (has_aes && has_sha)
		device_set_desc(dev,
		    "AES-CBC,AES-CCM,AES-GCM,AES-ICM,AES-XTS,SHA1,SHA256");
	else if (has_aes)
		device_set_desc(dev,
		    "AES-CBC,AES-CCM,AES-GCM,AES-ICM,AES-XTS");
	else
		device_set_desc(dev, "SHA1,SHA256");

	return (0);
}