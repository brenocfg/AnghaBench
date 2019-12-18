#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  tv ;
typedef  void* time_t ;
struct timeval {int tv_sec; void* tv_usec; } ;
typedef  int /*<<< orphan*/ * plist_t ;
typedef  TYPE_1__* lockdownd_service_descriptor_t ;
typedef  int lockdownd_error_t ;
typedef  int /*<<< orphan*/ * lockdownd_client_t ;
typedef  int /*<<< orphan*/ * idevice_t ;
typedef  char* idevice_connection_t ;
struct TYPE_3__ {int ssl_enabled; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int INVALID_SOCKET ; 
 int LOCKDOWN_E_SUCCESS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ idevice_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ idevice_connection_enable_ssl (char*) ; 
 scalar_t__ idevice_connection_get_fd (char*,int*) ; 
 scalar_t__ idevice_connection_get_ssl_session (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  idevice_free (int /*<<< orphan*/ *) ; 
 scalar_t__ idevice_new (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lockdownd_client_free (int /*<<< orphan*/ *) ; 
 int lockdownd_client_new_with_handshake (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  lockdownd_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ lockdownd_start_service (int /*<<< orphan*/ *,char*,TYPE_1__**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  plist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_get_string_val (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int sscanf (char*,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 

int wi_connect(const char *device_id, char **to_device_id,
    char **to_device_name, int *to_device_os_version,
    void **to_ssl_session, int recv_timeout) {
  int ret = -1;

  idevice_t phone = NULL;
  plist_t node = NULL;
  lockdownd_service_descriptor_t service = NULL;
  lockdownd_client_t client = NULL;
  idevice_connection_t connection = NULL;
  int fd = -1;
  SSL *ssl_session = NULL;

  // get phone
  if (idevice_new(&phone, device_id)) {
    fprintf(stderr, "No device found, is it plugged in?\n");
    goto leave_cleanup;
  }

  // connect to lockdownd
  lockdownd_error_t ldret;
  if (LOCKDOWN_E_SUCCESS != (ldret = lockdownd_client_new_with_handshake(
        phone, &client, "ios_webkit_debug_proxy"))) {
    fprintf(stderr, "Could not connect to lockdownd, error code %d. Exiting.\n", ldret);
    goto leave_cleanup;
  }

  // get device info
  if (to_device_id &&
      !lockdownd_get_value(client, NULL, "UniqueDeviceID", &node)) {
    plist_get_string_val(node, to_device_id);
    plist_free(node);
    node = NULL;
  }
  if (to_device_name &&
      !lockdownd_get_value(client, NULL, "DeviceName", &node)) {
    plist_get_string_val(node, to_device_name);
    plist_free(node);
    node = NULL;
  }
  if (to_device_os_version &&
      !lockdownd_get_value(client, NULL, "ProductVersion", &node)) {
    int vers[3] = {0, 0, 0};
    char *s_version = NULL;
    plist_get_string_val(node, &s_version);
    if (s_version && sscanf(s_version, "%d.%d.%d",
          &vers[0], &vers[1], &vers[2]) >= 2) {
      *to_device_os_version = ((vers[0] & 0xFF) << 16) |
                              ((vers[1] & 0xFF) << 8)  |
                               (vers[2] & 0xFF);
    } else {
      *to_device_os_version = 0;
    }
    free(s_version);
    plist_free(node);
  }

  // start webinspector, get port
  if (lockdownd_start_service(client, "com.apple.webinspector", &service) ||
      !service->port) {
    perror("Could not start com.apple.webinspector!");
    goto leave_cleanup;
  }

  // connect to webinspector
  if (idevice_connect(phone, service->port, &connection)) {
    perror("idevice_connect failed!");
    goto leave_cleanup;
  }

  // enable ssl
  if (service->ssl_enabled == 1) {
    if (!to_ssl_session || idevice_connection_enable_ssl(connection) ||
        idevice_connection_get_ssl_session(connection, &ssl_session)) {
      perror("ssl connection failed!");
      goto leave_cleanup;
    }
    *to_ssl_session = ssl_session;
  }

  if (client) {
    // not needed anymore
    lockdownd_client_free(client);
    client = NULL;
  }

  // extract the connection fd
  if (idevice_connection_get_fd(connection, &fd)) {
    perror("Unable to get connection file descriptor.");
    goto leave_cleanup;
  }

  if (recv_timeout < 0) {
#ifdef WIN32
    u_long nb = 1;
    if (ioctlsocket(fd, FIONBIO, &nb)) {
      fprintf(stderr, "webinspector: could not set socket to non-blocking");
    }
#else
    int opts = fcntl(fd, F_GETFL);
    if (!opts || fcntl(fd, F_SETFL, (opts | O_NONBLOCK)) < 0) {
      perror("Could not set socket to non-blocking");
      goto leave_cleanup;
    }
#endif
  } else {
    long millis = (recv_timeout > 0 ? recv_timeout : 5000);
    struct timeval tv;
    tv.tv_sec = (time_t) (millis / 1000);
    tv.tv_usec = (time_t) ((millis - (tv.tv_sec * 1000)) * 1000);
    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,
          sizeof(tv))) {
      perror("Could not set socket receive timeout");
      goto leave_cleanup;
    }
  }

  // success
  ret = fd;

leave_cleanup:
#ifdef WIN32
  if (ret < 0 && fd != INVALID_SOCKET) {
    closesocket(fd);
  }
#else
  if (ret < 0 && fd > 0) {
    close(fd);
  }
#endif
  // don't call usbmuxd_disconnect(fd)!
  //idevice_disconnect(connection);
  free(connection);
  lockdownd_client_free(client);
  idevice_free(phone);
  return ret;
}