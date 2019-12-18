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
struct src_head {int dummy; } ;
struct _region {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (struct src_head*) ; 
 int /*<<< orphan*/  _region_head (struct _region*) ; 
 int /*<<< orphan*/  _region_size (struct _region*) ; 
 int convert_line (struct src_head*,char*,size_t) ; 
 int dump_db (struct src_head*,struct _region*) ; 
 int errno ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free_src (struct src_head*) ; 
 int fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
_citrus_pivot_factory_convert(FILE *out, FILE *in)
{
	struct src_head sh;
	struct _region r;
	char *line;
	size_t size;
	int ret;

	STAILQ_INIT(&sh);

	while ((line = fgetln(in, &size)) != NULL)
		if ((ret = convert_line(&sh, line, size))) {
			free_src(&sh);
			return (ret);
		}

	ret = dump_db(&sh, &r);
	free_src(&sh);
	if (ret)
		return (ret);

	if (fwrite(_region_head(&r), _region_size(&r), 1, out) != 1)
		return (errno);

	return (0);
}