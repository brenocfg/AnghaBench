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
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct upload_pack_data {int /*<<< orphan*/  writer; TYPE_1__ haves; } ;
struct repository {int dummy; } ;
struct packet_reader {int dummy; } ;
struct object_array {int /*<<< orphan*/  nr; } ;
struct argv_array {int dummy; } ;
typedef  enum fetch_state { ____Placeholder_fetch_state } fetch_state ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_FLAGS ; 
#define  FETCH_DONE 131 
#define  FETCH_PROCESS_ARGS 130 
#define  FETCH_SEND_ACKS 129 
#define  FETCH_SEND_PACK 128 
 int /*<<< orphan*/  LARGE_PACKET_MAX ; 
 struct object_array OBJECT_ARRAY_INIT ; 
 int /*<<< orphan*/  clear_object_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_pack_file (struct object_array*,struct object_array*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_array_clear (struct object_array*) ; 
 int /*<<< orphan*/  packet_writer_write (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  process_args (struct packet_reader*,struct upload_pack_data*,struct object_array*) ; 
 int /*<<< orphan*/  process_haves_and_send_acks (struct upload_pack_data*,struct object_array*,struct object_array*) ; 
 int /*<<< orphan*/  send_shallow_info (struct upload_pack_data*,struct object_array*) ; 
 int /*<<< orphan*/  send_wanted_ref_info (struct upload_pack_data*) ; 
 int /*<<< orphan*/  upload_pack_config ; 
 int /*<<< orphan*/  upload_pack_data_clear (struct upload_pack_data*) ; 
 int /*<<< orphan*/  upload_pack_data_init (struct upload_pack_data*) ; 
 int /*<<< orphan*/  use_sideband ; 

int upload_pack_v2(struct repository *r, struct argv_array *keys,
		   struct packet_reader *request)
{
	enum fetch_state state = FETCH_PROCESS_ARGS;
	struct upload_pack_data data;
	struct object_array have_obj = OBJECT_ARRAY_INIT;
	struct object_array want_obj = OBJECT_ARRAY_INIT;

	clear_object_flags(ALL_FLAGS);

	git_config(upload_pack_config, NULL);

	upload_pack_data_init(&data);
	use_sideband = LARGE_PACKET_MAX;

	while (state != FETCH_DONE) {
		switch (state) {
		case FETCH_PROCESS_ARGS:
			process_args(request, &data, &want_obj);

			if (!want_obj.nr) {
				/*
				 * Request didn't contain any 'want' lines,
				 * guess they didn't want anything.
				 */
				state = FETCH_DONE;
			} else if (data.haves.nr) {
				/*
				 * Request had 'have' lines, so lets ACK them.
				 */
				state = FETCH_SEND_ACKS;
			} else {
				/*
				 * Request had 'want's but no 'have's so we can
				 * immedietly go to construct and send a pack.
				 */
				state = FETCH_SEND_PACK;
			}
			break;
		case FETCH_SEND_ACKS:
			if (process_haves_and_send_acks(&data, &have_obj,
							&want_obj))
				state = FETCH_SEND_PACK;
			else
				state = FETCH_DONE;
			break;
		case FETCH_SEND_PACK:
			send_wanted_ref_info(&data);
			send_shallow_info(&data, &want_obj);

			packet_writer_write(&data.writer, "packfile\n");
			create_pack_file(&have_obj, &want_obj);
			state = FETCH_DONE;
			break;
		case FETCH_DONE:
			continue;
		}
	}

	upload_pack_data_clear(&data);
	object_array_clear(&have_obj);
	object_array_clear(&want_obj);
	return 0;
}