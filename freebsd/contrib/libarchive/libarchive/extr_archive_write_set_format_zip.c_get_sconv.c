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
struct zip {int init_default_conversion; struct archive_string_conv* sconv_default; struct archive_string_conv* opt_sconv; } ;
struct archive_write {int /*<<< orphan*/  archive; } ;
struct archive_string_conv {int dummy; } ;

/* Variables and functions */
 struct archive_string_conv* archive_string_default_conversion_for_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct archive_string_conv *
get_sconv(struct archive_write *a, struct zip *zip)
{
	if (zip->opt_sconv != NULL)
		return (zip->opt_sconv);

	if (!zip->init_default_conversion) {
		zip->sconv_default =
		    archive_string_default_conversion_for_write(&(a->archive));
		zip->init_default_conversion = 1;
	}
	return (zip->sconv_default);
}