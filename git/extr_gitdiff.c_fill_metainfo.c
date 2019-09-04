#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct TYPE_3__ {scalar_t__ binary; scalar_t__ full_index; } ;
struct diff_options {int /*<<< orphan*/  repo; TYPE_1__ flags; } ;
struct diff_filespec {char const* mode; int /*<<< orphan*/  oid; } ;
struct diff_filepair {int status; int /*<<< orphan*/  score; } ;
typedef  int /*<<< orphan*/  mmfile_t ;
struct TYPE_4__ {unsigned int hexsz; } ;

/* Variables and functions */
 unsigned int const DEFAULT_ABBREV ; 
 int /*<<< orphan*/  DIFF_METAINFO ; 
 int /*<<< orphan*/  DIFF_RESET ; 
#define  DIFF_STATUS_COPIED 130 
#define  DIFF_STATUS_MODIFIED 129 
#define  DIFF_STATUS_RENAMED 128 
 int PATH_MAX ; 
 int /*<<< orphan*/  diff_abbrev_oid (int /*<<< orphan*/ *,int) ; 
 scalar_t__ diff_filespec_is_binary (int /*<<< orphan*/ ,struct diff_filespec*) ; 
 char* diff_get_color (int,int /*<<< orphan*/ ) ; 
 char* diff_line_prefix (struct diff_options*) ; 
 int /*<<< orphan*/  fill_mmfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct diff_filespec*) ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quote_c_style (char const*,struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  similarity_index (struct diff_filepair*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 TYPE_2__* the_hash_algo ; 

__attribute__((used)) static void fill_metainfo(struct strbuf *msg,
			  const char *name,
			  const char *other,
			  struct diff_filespec *one,
			  struct diff_filespec *two,
			  struct diff_options *o,
			  struct diff_filepair *p,
			  int *must_show_header,
			  int use_color)
{
	const char *set = diff_get_color(use_color, DIFF_METAINFO);
	const char *reset = diff_get_color(use_color, DIFF_RESET);
	const char *line_prefix = diff_line_prefix(o);

	*must_show_header = 1;
	strbuf_init(msg, PATH_MAX * 2 + 300);
	switch (p->status) {
	case DIFF_STATUS_COPIED:
		strbuf_addf(msg, "%s%ssimilarity index %d%%",
			    line_prefix, set, similarity_index(p));
		strbuf_addf(msg, "%s\n%s%scopy from ",
			    reset,  line_prefix, set);
		quote_c_style(name, msg, NULL, 0);
		strbuf_addf(msg, "%s\n%s%scopy to ", reset, line_prefix, set);
		quote_c_style(other, msg, NULL, 0);
		strbuf_addf(msg, "%s\n", reset);
		break;
	case DIFF_STATUS_RENAMED:
		strbuf_addf(msg, "%s%ssimilarity index %d%%",
			    line_prefix, set, similarity_index(p));
		strbuf_addf(msg, "%s\n%s%srename from ",
			    reset, line_prefix, set);
		quote_c_style(name, msg, NULL, 0);
		strbuf_addf(msg, "%s\n%s%srename to ",
			    reset, line_prefix, set);
		quote_c_style(other, msg, NULL, 0);
		strbuf_addf(msg, "%s\n", reset);
		break;
	case DIFF_STATUS_MODIFIED:
		if (p->score) {
			strbuf_addf(msg, "%s%sdissimilarity index %d%%%s\n",
				    line_prefix,
				    set, similarity_index(p), reset);
			break;
		}
		/* fallthru */
	default:
		*must_show_header = 0;
	}
	if (one && two && !oideq(&one->oid, &two->oid)) {
		const unsigned hexsz = the_hash_algo->hexsz;
		int abbrev = o->flags.full_index ? hexsz : DEFAULT_ABBREV;

		if (o->flags.binary) {
			mmfile_t mf;
			if ((!fill_mmfile(o->repo, &mf, one) &&
			     diff_filespec_is_binary(o->repo, one)) ||
			    (!fill_mmfile(o->repo, &mf, two) &&
			     diff_filespec_is_binary(o->repo, two)))
				abbrev = hexsz;
		}
		strbuf_addf(msg, "%s%sindex %s..%s", line_prefix, set,
			    diff_abbrev_oid(&one->oid, abbrev),
			    diff_abbrev_oid(&two->oid, abbrev));
		if (one->mode == two->mode)
			strbuf_addf(msg, " %06o", one->mode);
		strbuf_addf(msg, "%s\n", reset);
	}
}