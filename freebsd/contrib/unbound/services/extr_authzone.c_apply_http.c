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
struct sldns_file_parse_state {int default_ttl; int origin_len; char* origin; int /*<<< orphan*/  lineno; } ;
struct sldns_buffer {int dummy; } ;
struct auth_zone {int /*<<< orphan*/  data; } ;
struct auth_xfer {int namelen; TYPE_2__* task_transfer; scalar_t__ serial; scalar_t__ have_zone; int /*<<< orphan*/  name; } ;
struct auth_chunk {int len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  pstate ;
typedef  int /*<<< orphan*/  preview ;
struct TYPE_4__ {TYPE_1__* master; struct auth_chunk* chunks_first; } ;
struct TYPE_3__ {int /*<<< orphan*/  file; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  auth_data_cmp ; 
 int /*<<< orphan*/  auth_data_del ; 
 scalar_t__ chunkline_get_line_collated (struct auth_chunk**,size_t*,struct sldns_buffer*) ; 
 scalar_t__ chunkline_is_comment_line_or_empty (struct sldns_buffer*) ; 
 int /*<<< orphan*/  chunkline_newline_removal (struct sldns_buffer*) ; 
 scalar_t__ chunklist_sum (struct auth_chunk*) ; 
 int /*<<< orphan*/  http_parse_add_rr (struct auth_xfer*,struct auth_zone*,struct sldns_buffer*,struct sldns_file_parse_state*) ; 
 scalar_t__ http_parse_origin (struct sldns_buffer*,struct sldns_file_parse_state*) ; 
 scalar_t__ http_parse_ttl (struct sldns_buffer*,struct sldns_file_parse_state*) ; 
 int /*<<< orphan*/  http_zonefile_syntax_check (struct auth_xfer*,struct sldns_buffer*) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_info (char*,char*) ; 
 int /*<<< orphan*/  memmove (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sldns_file_parse_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_begin (struct sldns_buffer*) ; 
 int /*<<< orphan*/  traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*,int /*<<< orphan*/ ,int,...) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int
apply_http(struct auth_xfer* xfr, struct auth_zone* z,
	struct sldns_buffer* scratch_buffer)
{
	/* parse data in chunks */
	/* parse RR's and read into memory. ignore $INCLUDE from the
	 * downloaded file*/
	struct sldns_file_parse_state pstate;
	struct auth_chunk* chunk;
	size_t chunk_pos;
	memset(&pstate, 0, sizeof(pstate));
	pstate.default_ttl = 3600;
	if(xfr->namelen < sizeof(pstate.origin)) {
		pstate.origin_len = xfr->namelen;
		memmove(pstate.origin, xfr->name, xfr->namelen);
	}

	if(verbosity >= VERB_ALGO)
		verbose(VERB_ALGO, "http download %s of size %d",
		xfr->task_transfer->master->file,
		(int)chunklist_sum(xfr->task_transfer->chunks_first));
	if(xfr->task_transfer->chunks_first && verbosity >= VERB_ALGO) {
		char preview[1024];
		if(xfr->task_transfer->chunks_first->len+1 > sizeof(preview)) {
			memmove(preview, xfr->task_transfer->chunks_first->data,
				sizeof(preview)-1);
			preview[sizeof(preview)-1]=0;
		} else {
			memmove(preview, xfr->task_transfer->chunks_first->data,
				xfr->task_transfer->chunks_first->len);
			preview[xfr->task_transfer->chunks_first->len]=0;
		}
		log_info("auth zone http downloaded content preview: %s",
			preview);
	}

	/* perhaps a little syntax check before we try to apply the data? */
	if(!http_zonefile_syntax_check(xfr, scratch_buffer)) {
		log_err("http download %s/%s does not contain a zonefile, "
			"but got '%s'", xfr->task_transfer->master->host,
			xfr->task_transfer->master->file,
			sldns_buffer_begin(scratch_buffer));
		return 0;
	}

	/* clear the data tree */
	traverse_postorder(&z->data, auth_data_del, NULL);
	rbtree_init(&z->data, &auth_data_cmp);
	xfr->have_zone = 0;
	xfr->serial = 0;

	chunk = xfr->task_transfer->chunks_first;
	chunk_pos = 0;
	pstate.lineno = 0;
	while(chunkline_get_line_collated(&chunk, &chunk_pos, scratch_buffer)) {
		/* process this line */
		pstate.lineno++;
		chunkline_newline_removal(scratch_buffer);
		if(chunkline_is_comment_line_or_empty(scratch_buffer)) {
			continue;
		}
		/* parse line and add RR */
		if(http_parse_origin(scratch_buffer, &pstate)) {
			continue; /* $ORIGIN has been handled */
		}
		if(http_parse_ttl(scratch_buffer, &pstate)) {
			continue; /* $TTL has been handled */
		}
		if(!http_parse_add_rr(xfr, z, scratch_buffer, &pstate)) {
			verbose(VERB_ALGO, "error parsing line [%s:%d] %s",
				xfr->task_transfer->master->file,
				pstate.lineno,
				sldns_buffer_begin(scratch_buffer));
			return 0;
		}
	}
	return 1;
}