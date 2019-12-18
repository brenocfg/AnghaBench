#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t data_size; void* data; int /*<<< orphan*/ * data_type; } ;
typedef  TYPE_1__ splash_decoder_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ bootverbose ; 
 void* preload_fetch_addr (int /*<<< orphan*/ *) ; 
 size_t preload_fetch_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * preload_search_by_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,void*,size_t) ; 

__attribute__((used)) static int
splash_find_data(splash_decoder_t *decoder)
{
	caddr_t image_module;
	void *ptr;
	size_t sz;

	if (decoder->data_type == NULL)
		return (0);

	image_module = preload_search_by_type(decoder->data_type);
	if (image_module == NULL)
		return (ENOENT);

	ptr = preload_fetch_addr(image_module);
	sz = preload_fetch_size(image_module);
	if (ptr == NULL || sz == 0)
		return (ENOENT);

	if (bootverbose)
		printf("splash: image@%p, size:%zu\n", ptr, sz);

	decoder->data = ptr;
	decoder->data_size = sz;
	return (0);
}