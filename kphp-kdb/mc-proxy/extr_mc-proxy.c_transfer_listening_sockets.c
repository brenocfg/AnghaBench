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
struct memcache_server_functions {struct mc_cluster* info; } ;
struct mc_config {int clusters_num; struct mc_cluster* Clusters; } ;
struct mc_cluster {int other_cluster_no; scalar_t__ port; int server_socket; int cluster_no; int cluster_name; struct connection* listening_connection; int /*<<< orphan*/  mc_proxy_inbound; } ;
struct connection {scalar_t__ basic_type; int fd; int /*<<< orphan*/ * extra; } ;

/* Variables and functions */
 struct connection* Connections ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ct_inbound ; 
 int /*<<< orphan*/  ct_memcache_server ; 
 int /*<<< orphan*/  epoll_close (int) ; 
 int /*<<< orphan*/  force_clear_connection (struct connection*) ; 
 scalar_t__ init_listening_connection (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int max_connection ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,scalar_t__,int,...) ; 

int transfer_listening_sockets (struct mc_config *MC, struct mc_config *MC_Old) {
  int i, j, k;
  for (i = 0; i < MC->clusters_num; i++) {
    struct mc_cluster *C = &MC->Clusters[i];
    j = C->other_cluster_no;
    if (j >= 0) {
      assert (j < MC_Old->clusters_num);
      struct mc_cluster *OC = &MC_Old->Clusters[j];
      assert (OC->port == C->port && OC->other_cluster_no == i);
      C->server_socket = OC->server_socket;
      C->listening_connection = OC->listening_connection;
      OC->server_socket = -1;
      OC->listening_connection = 0;
      C->listening_connection->extra = &C->mc_proxy_inbound;
    } else {
      assert (init_listening_connection (C->server_socket, &ct_memcache_server, &C->mc_proxy_inbound) >= 0);
      C->listening_connection = Connections + C->server_socket;
    }
  }
  for (k = 0; k <= max_connection; k++) { 
    struct connection *c = Connections + k;
    if (c->basic_type != ct_inbound || c->fd != k) {
      continue;
    }
    struct mc_cluster *OC = ((struct memcache_server_functions *) c->extra)->info;
    assert (OC && &OC->mc_proxy_inbound == c->extra);
    j = OC->cluster_no;
    i = OC->other_cluster_no;
    assert (OC == &MC_Old->Clusters[j]);
    if (i >= 0) {
      struct mc_cluster *C = &MC->Clusters[i];
      assert (C->cluster_no == i && C->other_cluster_no == j);
      vkprintf (2, "transferring inbound connection #%d (port %d) from old cluster %d to new cluster %d\n", k, OC->port, j, i);
      c->extra = &C->mc_proxy_inbound;
    } else {
      vkprintf (2, "closing inbound connection #%d (port %d) belonging to old cluster %d, no new cluster\n", k, OC->port, j);
      force_clear_connection (c);
      epoll_close (k);
      close (k);
    }
  }
  for (i = 0; i < MC_Old->clusters_num; i++) {
    struct mc_cluster *OC = &MC_Old->Clusters[i];
    if (OC->other_cluster_no == -1) {
      assert (OC->server_socket >= 0);
      k = OC->server_socket;
      vkprintf (1, "closing unneeded listening connection #%d for port %d belonging to old cluster %d (%s)\n", k, OC->port, i, OC->cluster_name);
      force_clear_connection (&Connections[k]);
      epoll_close (k);
      close (k);
      OC->server_socket = -1;
      OC->listening_connection = 0;
    } else {
      assert (OC->server_socket == -1 && !OC->listening_connection);
    }
  }
  return 0;
}