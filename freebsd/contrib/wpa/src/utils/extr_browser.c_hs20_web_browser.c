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
struct browser_context {int success; int /*<<< orphan*/  title; int /*<<< orphan*/  hover_link; int /*<<< orphan*/ * win; } ;
typedef  int /*<<< orphan*/  ctx ;
typedef  int /*<<< orphan*/  WebKitWebView ;
typedef  int /*<<< orphan*/  WebKitWebSettings ;
typedef  int /*<<< orphan*/  SoupSession ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 char* FALSE ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_POLICY_NEVER ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW_TOPLEVEL ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 char* TRUE ; 
 int /*<<< orphan*/ * WEBKIT_WEB_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct browser_context*) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gtk_events_pending () ; 
 int /*<<< orphan*/  gtk_init_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_main () ; 
 int /*<<< orphan*/  gtk_main_iteration () ; 
 int /*<<< orphan*/ * gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_grab_focus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_window_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_default_size (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gtk_window_set_role (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct browser_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  view_cb_download_requested ; 
 int /*<<< orphan*/  view_cb_hovering_over_link ; 
 int /*<<< orphan*/  view_cb_mime_type_policy_decision ; 
 int /*<<< orphan*/  view_cb_notify_load_status ; 
 int /*<<< orphan*/  view_cb_notify_progress ; 
 int /*<<< orphan*/  view_cb_resource_request_starting ; 
 int /*<<< orphan*/  view_cb_title_changed ; 
 int /*<<< orphan*/ * webkit_get_default_session () ; 
 int /*<<< orphan*/ * webkit_web_view_get_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  webkit_web_view_load_uri (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  webkit_web_view_new () ; 
 int /*<<< orphan*/  win_cb_destroy ; 

int hs20_web_browser(const char *url)
{
	GtkWidget *scroll;
	SoupSession *s;
	WebKitWebView *view;
	WebKitWebSettings *settings;
	struct browser_context ctx;

	memset(&ctx, 0, sizeof(ctx));
	if (!gtk_init_check(NULL, NULL))
		return -1;

	s = webkit_get_default_session();
	g_object_set(G_OBJECT(s), "ssl-ca-file",
		     "/etc/ssl/certs/ca-certificates.crt", NULL);
	g_object_set(G_OBJECT(s), "ssl-strict", FALSE, NULL);

	ctx.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_role(GTK_WINDOW(ctx.win), "Hotspot 2.0 client");
	gtk_window_set_default_size(GTK_WINDOW(ctx.win), 800, 600);

	scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
				       GTK_POLICY_NEVER, GTK_POLICY_NEVER);

	g_signal_connect(G_OBJECT(ctx.win), "destroy",
			 G_CALLBACK(win_cb_destroy), &ctx);

	view = WEBKIT_WEB_VIEW(webkit_web_view_new());
	g_signal_connect(G_OBJECT(view), "notify::progress",
			 G_CALLBACK(view_cb_notify_progress), &ctx);
	g_signal_connect(G_OBJECT(view), "notify::load-status",
			 G_CALLBACK(view_cb_notify_load_status), &ctx);
	g_signal_connect(G_OBJECT(view), "resource-request-starting",
			 G_CALLBACK(view_cb_resource_request_starting), &ctx);
	g_signal_connect(G_OBJECT(view), "mime-type-policy-decision-requested",
			 G_CALLBACK(view_cb_mime_type_policy_decision), &ctx);
	g_signal_connect(G_OBJECT(view), "download-requested",
			 G_CALLBACK(view_cb_download_requested), &ctx);
	g_signal_connect(G_OBJECT(view), "hovering-over-link",
			 G_CALLBACK(view_cb_hovering_over_link), &ctx);
	g_signal_connect(G_OBJECT(view), "title-changed",
			 G_CALLBACK(view_cb_title_changed), &ctx);

	gtk_container_add(GTK_CONTAINER(scroll), GTK_WIDGET(view));
	gtk_container_add(GTK_CONTAINER(ctx.win), GTK_WIDGET(scroll));

	gtk_widget_grab_focus(GTK_WIDGET(view));
	gtk_widget_show_all(ctx.win);

	settings = webkit_web_view_get_settings(view);
	g_object_set(G_OBJECT(settings), "user-agent",
		     "Mozilla/5.0 (X11; U; Unix; en-US) "
		     "AppleWebKit/537.15 (KHTML, like Gecko) "
		     "hs20-client/1.0", NULL);
	g_object_set(G_OBJECT(settings), "auto-load-images", TRUE, NULL);

	webkit_web_view_load_uri(view, url);

	gtk_main();
	gtk_widget_destroy(ctx.win);
	while (gtk_events_pending())
		gtk_main_iteration();

	free(ctx.hover_link);
	free(ctx.title);
	return ctx.success;
}