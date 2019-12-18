#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  plist_t ;
typedef  TYPE_1__* dl_t ;
typedef  int /*<<< orphan*/  dl_status ;
struct TYPE_4__ {int /*<<< orphan*/  (* send_packet ) (TYPE_1__*,char*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DL_ERROR ; 
 int TYPE_PLIST ; 
 scalar_t__ calloc (size_t,int) ; 
 char* dl_sprintf_uint32 (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int plist_dict_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plist_dict_set_item (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plist_new_dict () ; 
 int /*<<< orphan*/  plist_new_string (char*) ; 
 int /*<<< orphan*/  plist_to_xml (int /*<<< orphan*/ ,char**,int*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,size_t) ; 

dl_status dl_start(dl_t self) {
  // Assume usbmuxd supports proto_version 1.  If not then we'd need to
  // send a binary listen request, check for failure, then retry this:
  plist_t dict = plist_new_dict();
  plist_dict_set_item(dict, "ClientVersionString", plist_new_string(
        "device_listener"));
  if (plist_dict_get_size(dict) != 1) {
    perror("Detected an old copy of libplist?!  For a fix, see:\n"
        "https://github.com/libimobiledevice/libimobiledevice/issues/"
        "68#issuecomment-38994545");
    return DL_ERROR;
  }
  plist_dict_set_item(dict, "MessageType", plist_new_string("Listen"));
  plist_dict_set_item(dict, "ProgName", plist_new_string("libusbmuxd"));
  char *xml = NULL;
  uint32_t xml_length = 0;
  plist_to_xml(dict, &xml, &xml_length);
  plist_free(dict);

  size_t length = 16 + xml_length;
  char *packet = (char *)calloc(length, sizeof(char));
  if (!packet) {
    return DL_ERROR;
  }
  char *tail = packet;
  tail = dl_sprintf_uint32(tail, length);
  tail = dl_sprintf_uint32(tail, 1); // version: 1
  tail = dl_sprintf_uint32(tail, TYPE_PLIST); // type: plist
  tail = dl_sprintf_uint32(tail, 1); // tag: 1
  strncpy(tail, xml, xml_length);
  free(xml);

  dl_status ret = self->send_packet(self, packet, length);
  free(packet);
  return ret;
}