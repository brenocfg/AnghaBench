#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ data_type_t ;
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ data_resource_t ;
struct TYPE_6__ {void* error; int /*<<< orphan*/ * file; int /*<<< orphan*/  xxhash64; } ;
typedef  TYPE_2__ curl_data_t ;

/* Variables and functions */
 void* ENOMEM ; 
 int /*<<< orphan*/  UTIL_isDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* cat3 (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ data_type_file ; 
 void* errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_data_dir ; 
 void* popen (char*,char*) ; 

__attribute__((used)) static curl_data_t curl_data_create(
    data_resource_t const* resource,
    data_type_t type) {
    curl_data_t cdata = {};

    XXH64_reset(&cdata.xxhash64, 0);

    assert(UTIL_isDirectory(g_data_dir));

    if (type == data_type_file) {
        /* Decompress the resource and store to the path. */
        char* cmd = cat3("zstd -dqfo '", resource->path, "'");
        if (cmd == NULL) {
            cdata.error = ENOMEM;
            return cdata;
        }
        cdata.file = popen(cmd, "w");
        free(cmd);
    } else {
        /* Decompress and extract the resource to the cache directory. */
        char* cmd = cat3("zstd -dc | tar -x -C '", g_data_dir, "'");
        if (cmd == NULL) {
            cdata.error = ENOMEM;
            return cdata;
        }
        cdata.file = popen(cmd, "w");
        free(cmd);
    }
    if (cdata.file == NULL) {
        cdata.error = errno;
    }

    return cdata;
}