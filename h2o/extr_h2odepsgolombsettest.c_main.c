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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  keys ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ golombset_decode (int,unsigned char*,size_t,int*,size_t*) ; 
 scalar_t__ golombset_encode (int,int*,size_t const,unsigned char*,size_t*) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  printf (char*,size_t const,size_t) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    uint64_t keys[] = {151, 192,  208,  269,  461,  512,  526,  591,  662,  806,  831,  866,  890,
                       997, 1005, 1017, 1134, 1207, 1231, 1327, 1378, 1393, 1418, 1525, 1627, 1630};
    const size_t num_keys = sizeof(keys) / sizeof(keys[0]);
    unsigned char buf[1024];
    size_t bufsize = sizeof(buf);

    if (golombset_encode(6, keys, num_keys, buf, &bufsize) != 0) {
        fprintf(stderr, "golombset_encode failed\n");
        return 111;
    }
    printf("encoded %zu entries into %zu bytes\n", num_keys, bufsize);
    
    uint64_t decoded_keys[num_keys];
    size_t num_decoded_keys = num_keys;
    if (golombset_decode(6, buf, bufsize, decoded_keys, &num_decoded_keys) != 0) {
        fprintf(stderr, "golombset_decode failed\n");
        return 111;
    }

    if (num_decoded_keys != num_keys) {
        fprintf(stderr, "unexpected number of outputs\n");
        return 111;
    }
    if (memcmp(keys, decoded_keys, sizeof(keys[0]) * num_keys) != 0) {
        fprintf(stderr, "output mismatch\n");
        return 111;
    }

    return 0;
}