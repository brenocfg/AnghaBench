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
struct sliding_view {int /*<<< orphan*/  buf; } ;
struct line_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 struct line_buffer LINE_BUFFER_INIT ; 
 struct sliding_view SLIDING_VIEW_INIT (struct line_buffer*,int) ; 
 scalar_t__ buffer_deinit (struct line_buffer*) ; 
 scalar_t__ buffer_init (struct line_buffer*,char const*) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 scalar_t__ strtoumax (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svndiff0_apply (struct line_buffer*,int /*<<< orphan*/ ,struct sliding_view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_svnfe_usage ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_delta(int argc, const char **argv)
{
	struct line_buffer preimage = LINE_BUFFER_INIT;
	struct line_buffer delta = LINE_BUFFER_INIT;
	struct sliding_view preimage_view = SLIDING_VIEW_INIT(&preimage, -1);

	if (argc != 5)
		usage(test_svnfe_usage);

	if (buffer_init(&preimage, argv[2]))
		die_errno("cannot open preimage");
	if (buffer_init(&delta, argv[3]))
		die_errno("cannot open delta");
	if (svndiff0_apply(&delta, (off_t) strtoumax(argv[4], NULL, 0),
					&preimage_view, stdout))
		return 1;
	if (buffer_deinit(&preimage))
		die_errno("cannot close preimage");
	if (buffer_deinit(&delta))
		die_errno("cannot close delta");
	strbuf_release(&preimage_view.buf);
	return 0;
}