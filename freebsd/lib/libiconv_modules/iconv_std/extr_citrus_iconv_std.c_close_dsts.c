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
struct _citrus_iconv_std_dst_list {int dummy; } ;
struct _citrus_iconv_std_dst {int /*<<< orphan*/  sd_mapper; } ;

/* Variables and functions */
 struct _citrus_iconv_std_dst* TAILQ_FIRST (struct _citrus_iconv_std_dst_list*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct _citrus_iconv_std_dst_list*,struct _citrus_iconv_std_dst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _csmapper_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct _citrus_iconv_std_dst*) ; 
 int /*<<< orphan*/  sd_entry ; 

__attribute__((used)) static void
close_dsts(struct _citrus_iconv_std_dst_list *dl)
{
	struct _citrus_iconv_std_dst *sd;

	while ((sd = TAILQ_FIRST(dl)) != NULL) {
		TAILQ_REMOVE(dl, sd, sd_entry);
		_csmapper_close(sd->sd_mapper);
		free(sd);
	}
}