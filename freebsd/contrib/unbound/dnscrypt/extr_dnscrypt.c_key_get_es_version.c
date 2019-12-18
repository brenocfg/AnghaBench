#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int member_0; int member_1; } ;

/* Variables and functions */

__attribute__((used)) static const char *
key_get_es_version(uint8_t version[2])
{
    struct es_version {
        uint8_t es_version[2];
        const char *name;
    };

    const int num_versions = 2;
    struct es_version es_versions[] = {
        {{0x00, 0x01}, "X25519-XSalsa20Poly1305"},
        {{0x00, 0x02}, "X25519-XChacha20Poly1305"},
    };
    int i;
    for(i=0; i < num_versions; i++){
        if(es_versions[i].es_version[0] == version[0] &&
           es_versions[i].es_version[1] == version[1]){
            return es_versions[i].name;
        }
    }
    return NULL;
}