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
typedef  int /*<<< orphan*/  yrmcds_error ;
typedef  int /*<<< orphan*/  yrmcds_command ;
struct TYPE_4__ {size_t compress_size; } ;
typedef  TYPE_1__ yrmcds ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  extras ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4_compress (char const*,char*,int) ; 
 int /*<<< orphan*/  LZ4_compressBound (int) ; 
 int /*<<< orphan*/  YRMCDS_BAD_ARGUMENT ; 
 int /*<<< orphan*/  YRMCDS_COMPRESS_FAILED ; 
 int YRMCDS_FLAG_COMPRESS ; 
 int /*<<< orphan*/  YRMCDS_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  hton32 (int,char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  send_command (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t,char const*,int,char*,size_t,char const*) ; 

__attribute__((used)) static yrmcds_error send_data(
    yrmcds* c, yrmcds_command cmd, const char* key, size_t key_len,
    const char* data, size_t data_len, uint32_t flags, uint32_t expire,
    uint64_t cas, uint32_t* serial) {
    if( c == NULL || key == NULL || key_len == 0 ||
        data == NULL || data_len == 0 )
        return YRMCDS_BAD_ARGUMENT;

    int compressed = 0;
#ifdef LIBYRMCDS_USE_LZ4
    if( (c->compress_size > 0) && (data_len > c->compress_size) ) {
        if( flags & YRMCDS_FLAG_COMPRESS )
            return YRMCDS_BAD_ARGUMENT;

        size_t bound = (size_t)LZ4_compressBound((int)data_len);
        char* new_data = (char*)malloc(bound + sizeof(uint32_t));
        if( new_data == NULL )
            return YRMCDS_OUT_OF_MEMORY;
        uint32_t new_size =
            (uint32_t)LZ4_compress(data, new_data + sizeof(uint32_t),
                                   (int)data_len);
        if( new_size == 0 ) {
            free(new_data);
            return YRMCDS_COMPRESS_FAILED;
        }
        hton32((uint32_t)data_len, new_data);
        flags |= YRMCDS_FLAG_COMPRESS;
        data_len = sizeof(uint32_t) + new_size;
        data = new_data;
        compressed = 1;
    }
#endif // LIBYRMCDS_USE_LZ4

    char extras[8];
    hton32(flags, extras);
    hton32(expire, &extras[4]);
    yrmcds_error e = send_command(c, cmd, cas, serial, key_len, key,
                                  sizeof(extras), extras, data_len, data);
    if( compressed )
        free((void*)data);
    return e;
}