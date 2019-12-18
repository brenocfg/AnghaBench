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
struct TYPE_4__ {char* name; scalar_t__ data_size; int /*<<< orphan*/ * data; scalar_t__ (* init ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ splash_decoder_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  splash_adp ; 
 scalar_t__ splash_find_data (TYPE_1__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
splash_test(splash_decoder_t *decoder)
{
	if (splash_find_data(decoder))
		return ENOENT;	/* XXX */
	if (*decoder->init && (*decoder->init)(splash_adp)) {
		decoder->data = NULL;
		decoder->data_size = 0;
		return ENODEV;	/* XXX */
	}
	if (bootverbose)
		printf("splash: image decoder found: %s\n", decoder->name);
	return 0;
}