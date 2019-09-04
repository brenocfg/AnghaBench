#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct stat {scalar_t__ st_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  hash; } ;
struct http_object_request {int localfile; int http_code; scalar_t__ curl_result; scalar_t__ zret; int rename; TYPE_1__ tmpfile; int /*<<< orphan*/  oid; TYPE_3__ real_oid; int /*<<< orphan*/  c; int /*<<< orphan*/  stream; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* final_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ Z_STREAM_END ; 
 int /*<<< orphan*/  close (int) ; 
 int finalize_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_inflate_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loose_object_path (int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  process_http_object_request (struct http_object_request*) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*) ; 

int finish_http_object_request(struct http_object_request *freq)
{
	struct stat st;
	struct strbuf filename = STRBUF_INIT;

	close(freq->localfile);
	freq->localfile = -1;

	process_http_object_request(freq);

	if (freq->http_code == 416) {
		warning("requested range invalid; we may already have all the data.");
	} else if (freq->curl_result != CURLE_OK) {
		if (stat(freq->tmpfile.buf, &st) == 0)
			if (st.st_size == 0)
				unlink_or_warn(freq->tmpfile.buf);
		return -1;
	}

	git_inflate_end(&freq->stream);
	the_hash_algo->final_fn(freq->real_oid.hash, &freq->c);
	if (freq->zret != Z_STREAM_END) {
		unlink_or_warn(freq->tmpfile.buf);
		return -1;
	}
	if (!oideq(&freq->oid, &freq->real_oid)) {
		unlink_or_warn(freq->tmpfile.buf);
		return -1;
	}
	loose_object_path(the_repository, &filename, &freq->oid);
	freq->rename = finalize_object_file(freq->tmpfile.buf, filename.buf);
	strbuf_release(&filename);

	return freq->rename;
}