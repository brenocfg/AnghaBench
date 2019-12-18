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
struct upload_pack_options {scalar_t__ advertise_refs; int /*<<< orphan*/  daemon_mode; int /*<<< orphan*/  timeout; int /*<<< orphan*/  stateless_rpc; } ;
struct string_list {int dummy; } ;
struct packet_reader {int dummy; } ;
struct object_array {scalar_t__ nr; } ;

/* Variables and functions */
 struct object_array OBJECT_ARRAY_INIT ; 
 int PACKET_READ_CHOMP_NEWLINE ; 
 int PACKET_READ_DIE_ON_ERR_PACKET ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  advertise_shallow_grafts (int) ; 
 int /*<<< orphan*/  check_ref ; 
 int /*<<< orphan*/  create_pack_file (struct object_array*,struct object_array*) ; 
 int /*<<< orphan*/  daemon_mode ; 
 int /*<<< orphan*/  find_symref ; 
 int /*<<< orphan*/  for_each_namespaced_ref (int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  get_common_commits (struct packet_reader*,struct object_array*,struct object_array*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  head_ref_namespaced (int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  packet_flush (int) ; 
 int /*<<< orphan*/  packet_reader_init (struct packet_reader*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  receive_needs (struct packet_reader*,struct object_array*) ; 
 int /*<<< orphan*/  reset_timeout () ; 
 int /*<<< orphan*/  send_ref ; 
 int /*<<< orphan*/  stateless_rpc ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  upload_pack_config ; 

void upload_pack(struct upload_pack_options *options)
{
	struct string_list symref = STRING_LIST_INIT_DUP;
	struct object_array want_obj = OBJECT_ARRAY_INIT;
	struct packet_reader reader;

	stateless_rpc = options->stateless_rpc;
	timeout = options->timeout;
	daemon_mode = options->daemon_mode;

	git_config(upload_pack_config, NULL);

	head_ref_namespaced(find_symref, &symref);

	if (options->advertise_refs || !stateless_rpc) {
		reset_timeout();
		head_ref_namespaced(send_ref, &symref);
		for_each_namespaced_ref(send_ref, &symref);
		advertise_shallow_grafts(1);
		packet_flush(1);
	} else {
		head_ref_namespaced(check_ref, NULL);
		for_each_namespaced_ref(check_ref, NULL);
	}
	string_list_clear(&symref, 1);
	if (options->advertise_refs)
		return;

	packet_reader_init(&reader, 0, NULL, 0,
			   PACKET_READ_CHOMP_NEWLINE |
			   PACKET_READ_DIE_ON_ERR_PACKET);

	receive_needs(&reader, &want_obj);
	if (want_obj.nr) {
		struct object_array have_obj = OBJECT_ARRAY_INIT;
		get_common_commits(&reader, &have_obj, &want_obj);
		create_pack_file(&have_obj, &want_obj);
	}
}