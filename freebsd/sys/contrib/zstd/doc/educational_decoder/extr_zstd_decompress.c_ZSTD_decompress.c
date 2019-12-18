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
typedef  int /*<<< orphan*/  dictionary_t ;

/* Variables and functions */
 size_t ZSTD_decompress_with_dict (void* const,size_t const,void const* const,size_t const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_dictionary () ; 
 int /*<<< orphan*/  free_dictionary (int /*<<< orphan*/ *) ; 

size_t ZSTD_decompress(void *const dst, const size_t dst_len,
                       const void *const src, const size_t src_len) {
    dictionary_t* uninit_dict = create_dictionary();
    size_t const decomp_size = ZSTD_decompress_with_dict(dst, dst_len, src,
                                                         src_len, uninit_dict);
    free_dictionary(uninit_dict);
    return decomp_size;
}