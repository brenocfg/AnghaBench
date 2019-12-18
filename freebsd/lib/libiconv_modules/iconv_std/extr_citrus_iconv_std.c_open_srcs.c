#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct _esdb {int db_num_charsets; TYPE_1__* db_charsets; } ;
struct _citrus_iconv_std_src_list {int dummy; } ;
struct _citrus_iconv_std_src {int /*<<< orphan*/  ss_dsts; int /*<<< orphan*/  ss_csid; } ;
struct TYPE_2__ {int /*<<< orphan*/  ec_csid; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct _citrus_iconv_std_src_list*,struct _citrus_iconv_std_src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_srcs (struct _citrus_iconv_std_src_list*) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct _citrus_iconv_std_src*) ; 
 struct _citrus_iconv_std_src* malloc (int) ; 
 int open_dsts (int /*<<< orphan*/ *,TYPE_1__*,struct _esdb const*) ; 
 int /*<<< orphan*/  ss_entry ; 

__attribute__((used)) static int
open_srcs(struct _citrus_iconv_std_src_list *sl,
    const struct _esdb *dbsrc, const struct _esdb *dbdst)
{
	struct _citrus_iconv_std_src *ss;
	int count = 0, i, ret;

	ss = malloc(sizeof(*ss));
	if (ss == NULL)
		return (errno);

	TAILQ_INIT(&ss->ss_dsts);

	for (i = 0; i < dbsrc->db_num_charsets; i++) {
		ret = open_dsts(&ss->ss_dsts, &dbsrc->db_charsets[i], dbdst);
		if (ret)
			goto err;
		if (!TAILQ_EMPTY(&ss->ss_dsts)) {
			ss->ss_csid = dbsrc->db_charsets[i].ec_csid;
			TAILQ_INSERT_TAIL(sl, ss, ss_entry);
			ss = malloc(sizeof(*ss));
			if (ss == NULL) {
				ret = errno;
				goto err;
			}
			count++;
			TAILQ_INIT(&ss->ss_dsts);
		}
	}
	free(ss);

	return (count ? 0 : ENOENT);

err:
	free(ss);
	close_srcs(sl);
	return (ret);
}