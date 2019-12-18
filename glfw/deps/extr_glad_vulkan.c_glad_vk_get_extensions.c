#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ VkResult ;
typedef  int /*<<< orphan*/ * VkPhysicalDevice ;
struct TYPE_4__ {int /*<<< orphan*/  extensionName; } ;
typedef  TYPE_1__ VkExtensionProperties ;

/* Variables and functions */
 scalar_t__ VK_SUCCESS ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ vkEnumerateDeviceExtensionProperties (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,TYPE_1__*) ; 
 scalar_t__ vkEnumerateInstanceExtensionProperties (int /*<<< orphan*/ *,int*,TYPE_1__*) ; 

__attribute__((used)) static int glad_vk_get_extensions( VkPhysicalDevice physical_device, uint32_t *out_extension_count, char ***out_extensions) {
    uint32_t i;
    uint32_t instance_extension_count = 0;
    uint32_t device_extension_count = 0;
    uint32_t max_extension_count;
    uint32_t total_extension_count;
    char **extensions;
    VkExtensionProperties *ext_properties;
    VkResult result;

    if (vkEnumerateInstanceExtensionProperties == NULL || (physical_device != NULL && vkEnumerateDeviceExtensionProperties == NULL)) {
        return 0;
    }

    result = vkEnumerateInstanceExtensionProperties(NULL, &instance_extension_count, NULL);
    if (result != VK_SUCCESS) {
        return 0;
    }

    if (physical_device != NULL) {
        result = vkEnumerateDeviceExtensionProperties(physical_device, NULL, &device_extension_count, NULL);
        if (result != VK_SUCCESS) {
            return 0;
        }
    }

    total_extension_count = instance_extension_count + device_extension_count;
    max_extension_count = instance_extension_count > device_extension_count
        ? instance_extension_count : device_extension_count;

    ext_properties = (VkExtensionProperties*) malloc(max_extension_count * sizeof(VkExtensionProperties));
    if (ext_properties == NULL) {
        return 0;
    }

    result = vkEnumerateInstanceExtensionProperties(NULL, &instance_extension_count, ext_properties);
    if (result != VK_SUCCESS) {
        free((void*) ext_properties);
        return 0;
    }

    extensions = (char**) calloc(total_extension_count, sizeof(char*));
    if (extensions == NULL) {
        free((void*) ext_properties);
        return 0;
    }

    for (i = 0; i < instance_extension_count; ++i) {
        VkExtensionProperties ext = ext_properties[i];

        size_t extension_name_length = strlen(ext.extensionName) + 1;
        extensions[i] = (char*) malloc(extension_name_length * sizeof(char));
        memcpy(extensions[i], ext.extensionName, extension_name_length * sizeof(char));
    }

    if (physical_device != NULL) {
        result = vkEnumerateDeviceExtensionProperties(physical_device, NULL, &device_extension_count, ext_properties);
        if (result != VK_SUCCESS) {
            for (i = 0; i < instance_extension_count; ++i) {
                free((void*) extensions[i]);
            }
            free(extensions);
            return 0;
        }

        for (i = 0; i < device_extension_count; ++i) {
            VkExtensionProperties ext = ext_properties[i];

            size_t extension_name_length = strlen(ext.extensionName) + 1;
            extensions[instance_extension_count + i] = (char*) malloc(extension_name_length * sizeof(char));
            memcpy(extensions[instance_extension_count + i], ext.extensionName, extension_name_length * sizeof(char));
        }
    }

    free((void*) ext_properties);

    *out_extension_count = total_extension_count;
    *out_extensions = extensions;

    return 1;
}