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
struct la_zstream {int valid; int /*<<< orphan*/  end; int /*<<< orphan*/  code; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  compression_code_copy ; 
 int /*<<< orphan*/  compression_end (struct archive*,struct la_zstream*) ; 
 int /*<<< orphan*/  compression_end_copy ; 

__attribute__((used)) static int
compression_init_encoder_copy(struct archive *a, struct la_zstream *lastrm)
{

	if (lastrm->valid)
		compression_end(a, lastrm);
	lastrm->valid = 1;
	lastrm->code = compression_code_copy;
	lastrm->end = compression_end_copy;
	return (ARCHIVE_OK);
}