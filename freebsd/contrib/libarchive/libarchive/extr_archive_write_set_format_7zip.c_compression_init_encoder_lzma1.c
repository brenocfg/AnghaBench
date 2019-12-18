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
struct la_zstream {scalar_t__ valid; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  compression_end (struct archive*,struct la_zstream*) ; 
 int compression_unsupported_encoder (struct archive*,struct la_zstream*,char*) ; 

__attribute__((used)) static int
compression_init_encoder_lzma1(struct archive *a,
    struct la_zstream *lastrm, int level)
{

	(void) level; /* UNUSED */
	if (lastrm->valid)
		compression_end(a, lastrm);
	return (compression_unsupported_encoder(a, lastrm, "lzma"));
}